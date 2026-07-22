#include "GeneratorWindow.h"

#include "../Services/GeneratorService.h"

#include <QButtonGroup>
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QRadioButton>
#include <QScrollArea>
#include <QSpinBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include "../Utils/CSVExporter.h"
#include "../Utils/TXTExporter.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>

namespace PharmaTrack
{

GeneratorWindow::GeneratorWindow(QWidget *parent)
    : QWidget(parent),
      m_generatorService(new GeneratorService(this))
{
    createWidgets();
    createLayouts();
    createConnections();
    applyStyle();

    enableExportButtons(false);

    m_progressBar->setValue(0);
}

GeneratorWindow::~GeneratorWindow()
{
}
void GeneratorWindow::createWidgets()
{
    //////////////////////////////////////////////////////
    // Scroll Area
    //////////////////////////////////////////////////////

    m_scrollArea = new QScrollArea(this);
    m_containerWidget = new QWidget();

    //////////////////////////////////////////////////////
    // Header
    //////////////////////////////////////////////////////

    m_titleLabel =
            new QLabel("Serial Number Generator");

    //////////////////////////////////////////////////////
    // Batch Information
    //////////////////////////////////////////////////////

    m_batchGroup =
            new QGroupBox("Batch Information");

    m_batchNumberLabel =
            new QLabel("Batch Number");

    m_productNameLabel =
            new QLabel("Product Name");

    m_quantityLabel =
            new QLabel("Quantity");

    m_prefixLabel =
            new QLabel("Prefix (Optional)");

    m_batchNumberEdit =
            new QLineEdit();

    m_productNameEdit =
            new QLineEdit();

    m_quantitySpinBox =
            new QSpinBox();

    m_quantitySpinBox->setMinimum(1);
    m_quantitySpinBox->setMaximum(100000000);

    m_prefixEdit =
            new QLineEdit();

    //////////////////////////////////////////////////////
    // Serial Length
    //////////////////////////////////////////////////////

    m_serialGroup =
            new QGroupBox("Serial Length");

    m_length15Radio =
            new QRadioButton("15 Characters");

    m_length21Radio =
            new QRadioButton("21 Characters");

    m_length15Radio->setChecked(true);

    m_lengthGroup =
            new QButtonGroup(this);

    m_lengthGroup->addButton(m_length15Radio);
    m_lengthGroup->addButton(m_length21Radio);

    //////////////////////////////////////////////////////
    // Buttons
    //////////////////////////////////////////////////////

    m_generateButton =
            new QPushButton("Generate");

    m_exportCsvButton =
            new QPushButton("Export CSV");

    m_exportTxtButton =
            new QPushButton("Export TXT");

    //////////////////////////////////////////////////////
    // Progress
    //////////////////////////////////////////////////////

    m_progressGroup =
            new QGroupBox("Progress");

    m_progressLabel =
            new QLabel("Ready");

    m_progressBar =
            new QProgressBar();

    //////////////////////////////////////////////////////
    // Summary
    //////////////////////////////////////////////////////

    m_summaryGroup =
            new QGroupBox("Generation Summary");

    m_batchSummaryLabel =
            new QLabel("Batch : -");

    m_productSummaryLabel =
            new QLabel("Product : -");

    m_quantitySummaryLabel =
            new QLabel("Quantity : -");

    m_prefixSummaryLabel =
            new QLabel("Prefix : -");

    m_lengthSummaryLabel =
            new QLabel("Length : -");

    m_generatedSummaryLabel =
            new QLabel("Generated : -");

    m_timeSummaryLabel =
            new QLabel("Time : -");
m_speedSummaryLabel =
        new QLabel("Speed : -");
    //////////////////////////////////////////////////////
    // Preview
    //////////////////////////////////////////////////////

    m_previewGroup =
            new QGroupBox("Preview");

    m_previewTable =
            new QTableWidget();

    m_previewTable->setColumnCount(3);

QStringList headers;
headers << "#"
        << "Serial Number"
        << "Status";
    m_previewTable->setHorizontalHeaderLabels(headers);

    m_previewTable->horizontalHeader()
        ->setSectionResizeMode(0,
                               QHeaderView::ResizeToContents);

m_previewTable->horizontalHeader()
        ->setSectionResizeMode(1,
                               QHeaderView::Stretch);

m_previewTable->horizontalHeader()
        ->setSectionResizeMode(2,
                               QHeaderView::ResizeToContents);

    m_previewTable->verticalHeader()->hide();

    m_previewTable->setEditTriggers(
                QAbstractItemView::NoEditTriggers);

    m_previewTable->setSelectionBehavior(
                QAbstractItemView::SelectRows);

    m_previewTable->setSelectionMode(
                QAbstractItemView::SingleSelection);
}
void GeneratorWindow::createLayouts()
{
    QVBoxLayout *containerLayout =
            new QVBoxLayout(m_containerWidget);

    containerLayout->setSpacing(20);

    containerLayout->addWidget(m_titleLabel);

    //////////////////////////////////////////////////////
    // Batch Group
    //////////////////////////////////////////////////////

    QGridLayout *batchLayout =
            new QGridLayout();

    batchLayout->addWidget(
                m_batchNumberLabel,
                0,0);

    batchLayout->addWidget(
                m_batchNumberEdit,
                0,1);

    batchLayout->addWidget(
                m_productNameLabel,
                1,0);

    batchLayout->addWidget(
                m_productNameEdit,
                1,1);

    batchLayout->addWidget(
                m_quantityLabel,
                2,0);

    batchLayout->addWidget(
                m_quantitySpinBox,
                2,1);

    batchLayout->addWidget(
                m_prefixLabel,
                3,0);

    batchLayout->addWidget(
                m_prefixEdit,
                3,1);

    m_batchGroup->setLayout(batchLayout);

    containerLayout->addWidget(m_batchGroup);

    //////////////////////////////////////////////////////
    // Serial Length
    //////////////////////////////////////////////////////

    QVBoxLayout *serialLayout =
            new QVBoxLayout();

    serialLayout->addWidget(m_length15Radio);

    serialLayout->addWidget(m_length21Radio);

    m_serialGroup->setLayout(serialLayout);

    containerLayout->addWidget(m_serialGroup);

    //////////////////////////////////////////////////////
    // Buttons
    //////////////////////////////////////////////////////

    QHBoxLayout *buttonLayout =
            new QHBoxLayout();

    buttonLayout->addWidget(m_generateButton);

    buttonLayout->addStretch();

    buttonLayout->addWidget(m_exportCsvButton);

    buttonLayout->addWidget(m_exportTxtButton);

    containerLayout->addLayout(buttonLayout);

    //////////////////////////////////////////////////////
    // Progress
    //////////////////////////////////////////////////////

    QVBoxLayout *progressLayout =
            new QVBoxLayout();

    progressLayout->addWidget(m_progressLabel);

    progressLayout->addWidget(m_progressBar);

    m_progressGroup->setLayout(progressLayout);

    containerLayout->addWidget(m_progressGroup);

    //////////////////////////////////////////////////////
    // Summary
    //////////////////////////////////////////////////////

    QVBoxLayout *summaryLayout =
            new QVBoxLayout();

    summaryLayout->addWidget(m_batchSummaryLabel);
    summaryLayout->addWidget(m_productSummaryLabel);
    summaryLayout->addWidget(m_quantitySummaryLabel);
    summaryLayout->addWidget(m_prefixSummaryLabel);
    summaryLayout->addWidget(m_lengthSummaryLabel);
    summaryLayout->addWidget(m_generatedSummaryLabel);
    summaryLayout->addWidget(m_timeSummaryLabel);
summaryLayout->addWidget(m_speedSummaryLabel);
    m_summaryGroup->setLayout(summaryLayout);

    containerLayout->addWidget(m_summaryGroup);

    //////////////////////////////////////////////////////
    // Preview
    //////////////////////////////////////////////////////

    QVBoxLayout *previewLayout =
            new QVBoxLayout();

    previewLayout->addWidget(m_previewTable);

    m_previewGroup->setLayout(previewLayout);

    containerLayout->addWidget(m_previewGroup);

    //////////////////////////////////////////////////////
    // Scroll Area
    //////////////////////////////////////////////////////

    m_scrollArea->setWidget(m_containerWidget);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setFrameShape(QFrame::NoFrame);

    QVBoxLayout *mainLayout =
            new QVBoxLayout(this);

    mainLayout->setContentsMargins(0,0,0,0);

    mainLayout->addWidget(m_scrollArea);

    setLayout(mainLayout);
}

void GeneratorWindow::createConnections()
{
    connect(m_generateButton,
            &QPushButton::clicked,
            this,
            &GeneratorWindow::onGenerateClicked);

    connect(m_exportCsvButton,
            &QPushButton::clicked,
            this,
            &GeneratorWindow::onExportCsvClicked);

    connect(m_exportTxtButton,
            &QPushButton::clicked,
            this,
            &GeneratorWindow::onExportTxtClicked);

    connect(m_generatorService,
            &GeneratorService::generationStarted,
            this,
            &GeneratorWindow::onGenerationStarted);

    connect(m_generatorService,
            &GeneratorService::generationFinished,
            this,
            &GeneratorWindow::onGenerationFinished);

    connect(m_generatorService,
            &GeneratorService::progressChanged,
            this,
            &GeneratorWindow::onProgressChanged);
}
void GeneratorWindow::enableExportButtons(bool enable)
{
    m_exportCsvButton->setEnabled(enable);
    m_exportTxtButton->setEnabled(enable);
}   
void GeneratorWindow::clearResults()
{
    m_generationResult.serials.clear();
m_generationResult.generatedCount = 0;
m_generationResult.generationSeconds = 0.0;
m_generationResult.generationSpeed = 0.0;
    m_previewTable->setRowCount(0);

    m_progressBar->setValue(0);

    m_progressLabel->setText("Ready");

    enableExportButtons(false);

    m_batchSummaryLabel->setText("Batch : -");
    m_productSummaryLabel->setText("Product : -");
    m_quantitySummaryLabel->setText("Quantity : -");
    m_prefixSummaryLabel->setText("Prefix : -");
    m_lengthSummaryLabel->setText("Length : -");
    m_generatedSummaryLabel->setText("Generated : -");
    m_timeSummaryLabel->setText("Time : -");
    m_speedSummaryLabel->setText("Speed : -");
}
bool GeneratorWindow::validateInput()
{
    if(m_batchNumberEdit->text().trimmed().isEmpty())
        return false;

    if(m_productNameEdit->text().trimmed().isEmpty())
        return false;

    if(m_quantitySpinBox->value() <= 0)
        return false;

    return true;
}
Batch GeneratorWindow::createBatch() const
{
    Batch batch;

    batch.setBatchNumber(
                m_batchNumberEdit->text());

    batch.setProductName(
                m_productNameEdit->text());

    batch.setQuantity(
                m_quantitySpinBox->value());

    batch.setPrefix(
                m_prefixEdit->text());
    batch.setGeneratedAt(QDateTime::currentDateTime());
    if(m_length15Radio->isChecked())
        batch.setSerialLength(15);
    else
        batch.setSerialLength(21);
batch.setGeneratedAt(QDateTime::currentDateTime());
    return batch;
}
void GeneratorWindow::onGenerationStarted()
{
    m_generateButton->setEnabled(false);

    enableExportButtons(false);

    m_progressBar->setValue(0);

    m_progressLabel->setText("Generating serial numbers...");
}
void GeneratorWindow::onGenerationFinished()
{
    m_generateButton->setEnabled(true);

    m_progressBar->setValue(100);

    m_progressLabel->setText("Generation completed.");

    enableExportButtons(!m_generationResult.serials.isEmpty());
}
void GeneratorWindow::onProgressChanged(int percentage)
{
    m_progressBar->setValue(percentage);

    m_progressLabel->setText(
                QString("Generating... %1%")
                .arg(percentage));
}
void GeneratorWindow::populatePreview()
{
    m_previewTable->setRowCount(0);

    const int previewCount =
            qMin(20, m_generationResult.serials.size());

    m_previewTable->setRowCount(previewCount);

    for(int i = 0; i < previewCount; ++i)
    {
        const SerialNumber &serial =
                m_generationResult.serials.at(i);

        QTableWidgetItem *indexItem =
                new QTableWidgetItem(
                    QString::number(i + 1));

        QTableWidgetItem *serialItem =
                new QTableWidgetItem(
                    serial.serial());

        QTableWidgetItem *statusItem =
                new QTableWidgetItem(
                    "Generated");

        indexItem->setTextAlignment(Qt::AlignCenter);
        statusItem->setTextAlignment(Qt::AlignCenter);

        m_previewTable->setItem(i,0,indexItem);
        m_previewTable->setItem(i,1,serialItem);
        m_previewTable->setItem(i,2,statusItem);
    }
}
void GeneratorWindow::updateSummary()
{
    Batch batch = createBatch();

    m_batchSummaryLabel->setText(
            "Batch : " +
            batch.batchNumber());

    m_productSummaryLabel->setText(
            "Product : " +
            batch.productName());

    m_quantitySummaryLabel->setText(
            "Quantity : " +
            QString::number(batch.quantity()));

    m_prefixSummaryLabel->setText(
            "Prefix : " +
            batch.prefix());

    m_lengthSummaryLabel->setText(
            "Length : " +
            QString::number(batch.serialLength()));

    m_generatedSummaryLabel->setText(
            "Generated : " +
            QString::number(
                m_generationResult.generatedCount));

    m_timeSummaryLabel->setText(
            QString("Time : %1 sec")
            .arg(m_generationResult.generationSeconds,
                 0,
                 'f',
                 3));

    m_speedSummaryLabel->setText(
            QString("Speed : %1 serials/sec")
            .arg(m_generationResult.generationSpeed,
                 0,
                 'f',
                 0));
}

void GeneratorWindow::onGenerateClicked()
{
    clearResults();

    if(!validateInput())
    {
        QMessageBox::warning(
                    this,
                    "Validation",
                    "Please complete all required fields.");

        return;
    }

    Batch batch =
            createBatch();
m_currentBatch = batch;
    QString errorMessage;



    const bool success =
            m_generatorService->generate(
                batch,
                m_generationResult,
                errorMessage);


    if(!success)
    {
        QMessageBox::critical(
                    this,
                    "Generation Failed",
                    errorMessage);

        return;
    }

    populatePreview();

    updateSummary();

    enableExportButtons(true);
}
void GeneratorWindow::onExportCsvClicked()
{
    QString fileName =
            QFileDialog::getSaveFileName(
                this,
                "Export CSV",
                "",
                "CSV Files (*.csv)");

    if(fileName.isEmpty())
        return;

    QString errorMessage;

    if(!CSVExporter::exportFile(
        fileName,
        m_currentBatch,
        m_generationResult.serials,
        errorMessage))
    {
        QMessageBox::critical(
                    this,
                    "Export Failed",
                    errorMessage);

        return;
    }

    QMessageBox::information(
                this,
                "Export",
                "CSV exported successfully.");
}

void GeneratorWindow::onExportTxtClicked()
{
    QString fileName =
            QFileDialog::getSaveFileName(
                this,
                "Export TXT",
                "",
                "Text Files (*.txt)");

    if(fileName.isEmpty())
        return;

    QString errorMessage;

    if(!TXTExporter::exportFile(
        fileName,
        m_currentBatch,
        m_generationResult.serials,
        errorMessage))
    {
        QMessageBox::critical(
                    this,
                    "Export Failed",
                    errorMessage);

        return;
    }

    QMessageBox::information(
                this,
                "Export",
                "TXT exported successfully.");
}

void GeneratorWindow::applyStyle()
{
    setMinimumSize(1100, 750);

    setWindowTitle("Serial Number Generator");

    m_titleLabel->setAlignment(Qt::AlignCenter);

    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setBold(true);

    m_titleLabel->setFont(titleFont);

    QString groupStyle =
            "QGroupBox {"
            "font-size:15px;"
            "font-weight:bold;"
            "border:1px solid #C8C8C8;"
            "border-radius:8px;"
            "margin-top:12px;"
            "padding-top:10px;"
            "}"
            "QGroupBox::title {"
            "subcontrol-origin: margin;"
            "left:12px;"
            "padding:0 5px;"
            "}";

    m_batchGroup->setStyleSheet(groupStyle);
    m_serialGroup->setStyleSheet(groupStyle);
    m_progressGroup->setStyleSheet(groupStyle);
    m_summaryGroup->setStyleSheet(groupStyle);
    m_previewGroup->setStyleSheet(groupStyle);

    QString lineEditStyle =
            "QLineEdit {"
            "padding:8px;"
            "font-size:13px;"
            "border:1px solid #BDBDBD;"
            "border-radius:5px;"
            "}";

    m_batchNumberEdit->setStyleSheet(lineEditStyle);
    m_productNameEdit->setStyleSheet(lineEditStyle);
    m_prefixEdit->setStyleSheet(lineEditStyle);

    QString spinStyle =
            "QSpinBox {"
            "padding:8px;"
            "font-size:13px;"
            "border:1px solid #BDBDBD;"
            "border-radius:5px;"
            "}";

    m_quantitySpinBox->setStyleSheet(spinStyle);

    QString buttonStyle =
            "QPushButton {"
            "padding:10px 20px;"
            "font-size:13px;"
            "font-weight:bold;"
            "border-radius:6px;"
            "background:#1976D2;"
            "color:white;"
            "}"
            "QPushButton:hover {"
            "background:#1565C0;"
            "}"
            "QPushButton:pressed {"
            "background:#0D47A1;"
            "}"
            "QPushButton:disabled {"
            "background:#BDBDBD;"
            "color:#EEEEEE;"
            "}";

    m_generateButton->setStyleSheet(buttonStyle);
    m_exportCsvButton->setStyleSheet(buttonStyle);
    m_exportTxtButton->setStyleSheet(buttonStyle);

    m_generateButton->setMinimumHeight(40);
    m_exportCsvButton->setMinimumHeight(40);
    m_exportTxtButton->setMinimumHeight(40);

    m_progressBar->setMinimumHeight(28);

    m_previewTable->setAlternatingRowColors(true);
    m_previewTable->setSelectionBehavior(
                QAbstractItemView::SelectRows);
    m_previewTable->setSelectionMode(
                QAbstractItemView::SingleSelection);
    m_previewTable->setShowGrid(true);

    m_previewTable->verticalHeader()->setDefaultSectionSize(28);

    m_scrollArea->setWidgetResizable(true);
}

} 