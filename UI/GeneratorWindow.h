#ifndef PHARMATRACK_GENERATORWINDOW_H
#define PHARMATRACK_GENERATORWINDOW_H

#include <QWidget>
#include "../Models/GenerationResult.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QRadioButton;
class QButtonGroup;
class QProgressBar;
class QTableWidget;
class QGroupBox;
class QScrollArea;
class QSpinBox;

namespace PharmaTrack
{

class GeneratorService;
class Batch;
class SerialNumber;

class GeneratorWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GeneratorWindow(QWidget *parent = nullptr);
    ~GeneratorWindow();

private slots:

    void onGenerateClicked();

    void onExportCsvClicked();

    void onExportTxtClicked();

    void onGenerationStarted();

    void onGenerationFinished();

    void onProgressChanged(int percentage);

private:

    ////////////////////////////////////////////////////////
    /// UI Creation
    ////////////////////////////////////////////////////////

    void createWidgets();

    void createLayouts();

    void createConnections();

    void applyStyle();

    ////////////////////////////////////////////////////////
    /// Helper Functions
    ////////////////////////////////////////////////////////

    bool validateInput();

    Batch createBatch() const;

    void populatePreview();

    void updateSummary();

    void clearResults();

    void enableExportButtons(bool enable);

    ////////////////////////////////////////////////////////
    /// Main Layout
    ////////////////////////////////////////////////////////

    QScrollArea* m_scrollArea;

    QWidget* m_containerWidget;

    ////////////////////////////////////////////////////////
    /// Header
    ////////////////////////////////////////////////////////

    QLabel* m_titleLabel;

    ////////////////////////////////////////////////////////
    /// Batch Information
    ////////////////////////////////////////////////////////

    QGroupBox* m_batchGroup;

    QLabel* m_batchNumberLabel;
    QLabel* m_productNameLabel;
    QLabel* m_quantityLabel;
    QLabel* m_prefixLabel;

    QLineEdit* m_batchNumberEdit;
    QLineEdit* m_productNameEdit;
    QSpinBox* m_quantitySpinBox;
    QLineEdit* m_prefixEdit;

    ////////////////////////////////////////////////////////
    /// Serial Options
    ////////////////////////////////////////////////////////

    QGroupBox* m_serialGroup;

    QRadioButton* m_length15Radio;
    QRadioButton* m_length21Radio;

    QButtonGroup* m_lengthGroup;

    ////////////////////////////////////////////////////////
    /// Actions
    ////////////////////////////////////////////////////////

    QPushButton* m_generateButton;

    QPushButton* m_exportCsvButton;

    QPushButton* m_exportTxtButton;

    ////////////////////////////////////////////////////////
    /// Progress
    ////////////////////////////////////////////////////////

    QGroupBox* m_progressGroup;

    QLabel* m_progressLabel;

    QProgressBar* m_progressBar;

    ////////////////////////////////////////////////////////
    /// Summary
    ////////////////////////////////////////////////////////

    QGroupBox* m_summaryGroup;

    QLabel* m_batchSummaryLabel;
    QLabel* m_productSummaryLabel;
    QLabel* m_quantitySummaryLabel;
    QLabel* m_prefixSummaryLabel;
    QLabel* m_lengthSummaryLabel;
    QLabel* m_generatedSummaryLabel;
    QLabel* m_timeSummaryLabel;
    QLabel* m_speedSummaryLabel;

    ////////////////////////////////////////////////////////
    /// Preview
    ////////////////////////////////////////////////////////

    QGroupBox* m_previewGroup;

    QTableWidget* m_previewTable;

    ////////////////////////////////////////////////////////
    /// Data
    ////////////////////////////////////////////////////////

    GeneratorService* m_generatorService;

    GenerationResult m_generationResult;
};

}

#endif // PHARMATRACK_GENERATORWINDOW_H