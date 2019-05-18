#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene_size = QSize(923, 685);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0,  scene_size.width(), scene_size.height());
    draw_grid();
    draw_chords();
    ui->graphicsView->setScene(scene);

    scale = ui->scale_spinBox->value();

    ui->x_centr_left->setMaximum(scene_size.width()/2);
    ui->x_centr_left->setMinimum(-scene_size.width()/2);

    ui->h_r_height->setMaximum(scene_size.width()/2);
    ui->h_r_height->setMinimum(-scene_size.width()/2);

    ui->new_x->setMaximum(scene_size.width()/2);
    ui->new_x->setMinimum(-scene_size.width()/2);

    ui->new_y->setMaximum(scene_size.height()/2);
    ui->new_y->setMinimum(-scene_size.height()/2);

    ui->y_centr_top->setMaximum(scene_size.height()/2);
    ui->y_centr_top->setMinimum(-scene_size.height()/2);

    ui->v_r_lenght->setMaximum(scene_size.height()/2);
    ui->v_r_lenght->setMinimum(-scene_size.height()/2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw_chords()
{
    scene->addLine(0, scene_size.height()/2, scene_size.width(), scene_size.height()/2);
    scene->addLine(scene_size.width()/2, 0, scene_size.width()/2, scene_size.height());
}

void MainWindow::draw_grid()
{
    for (int i = scene_size.width()/2; i<scene_size.width(); i += 10)
    {
        scene->addLine(i, 0, i, scene_size.height(), grid_pen);
    }
    for (int i = scene_size.width()/2; i>0; i -= 10)
    {
        scene->addLine(i, 0, i, scene_size.height(), grid_pen);
    }

    for (int i = scene_size.height()/2; i<scene_size.height(); i += 10)
    {
        scene->addLine(0, i, scene_size.width(), i, grid_pen);
    }
    for (int i = scene_size.height()/2; i>0; i -= 10)
    {
        scene->addLine(0, i, scene_size.width(), i, grid_pen);
    }
}

void MainWindow::on_scale_spinBox_valueChanged(int s)
{
    ui->graphicsView->scale(1.0/scale , 1.0/scale);
    ui->graphicsView->scale(s, s);
    scale = s;
}

void MainWindow::on_add_ellips_clicked()
{
    if (ui->ellips_radioButton->isChecked()) draw_ellipse();
    if (ui->sqsare_radioButton->isChecked()) draw_square();
    if (ui->rhomb_radioButton->isChecked()) draw_rhomb();

    ui->statusBar->clearMessage();
    ui->statusBar->showMessage("Площадь последней фигуры " + QString::number(figures.back()->square()));
}

void MainWindow::on_del_last_clicked()
{
    if (figures.size() != 0)
    {
        scene->removeItem(scene->items().front());
        figures.pop_back();

        ui->statusBar->clearMessage();
        if (figures.size() != 0)
            ui->statusBar->showMessage("Площадь последней фигуры " + QString::number(figures.back()->square()));
    }
}

void MainWindow::on_move_button_clicked()
{
    if (figures.size() != 0)
    {
        scene->removeItem(scene->items().front());
        figures.back()->move(ui->new_x->value() + scene_size.width()/2, scene_size.height()/2 - ui->new_y->value());
        figures.back()->draw(scene);
    }
}

void MainWindow::on_rhomb_radioButton_toggled(bool checked)
{
    if (checked)
    {
        ui->label_s1->setText("Левая грань ромба");
        ui->label_s2->setText("Верхняя грань ромба");
        ui->label_s3->setText("Ширина ромба");
        ui->label_s4->setText("Высота грань ромба");
        ui->h_r_height->setEnabled(true);
    }
}

void MainWindow::on_sqsare_radioButton_toggled(bool checked)
{
    if (checked)
    {
        ui->label_s1->setText("Левая грань квадрата");
        ui->label_s2->setText("Верхняя грань квадрата");
        ui->label_s3->setText("Длина стороны квадрата");
        ui->label_s4->setText("");
        ui->h_r_height->setEnabled(false);
    }
}

void MainWindow::on_ellips_radioButton_toggled(bool checked)
{
    if (checked)
    {
        ui->label_s1->setText("X центр элипса");
        ui->label_s2->setText("Y центр эллипса");
        ui->label_s3->setText("Вертикальный радиус");
        ui->label_s4->setText("Горизонтальный радиус");
        ui->h_r_height->setEnabled(true);
    }
}

void MainWindow::draw_ellipse()
{
    QColorDialog* dialog = new QColorDialog();
    dialog->exec();
    QColor color = dialog->currentColor();
    delete dialog;

    int x_c = ui->x_centr_left->value() + scene_size.width()/2,
        y_c = scene_size.height()/2 - ui->y_centr_top->value(),
        h_r = ui->h_r_height->value(),
        v_r = ui->v_r_lenght->value();

    figures.push_back(std::shared_ptr<figure>(new ellipse(x_c, y_c, v_r, h_r, color, ui->angle_spinBox->value())));
    figures.back()->draw(scene);
}

void MainWindow::draw_square()
{
    QColorDialog* dialog = new QColorDialog();
    dialog->exec();
    QColor color = dialog->currentColor();
    delete dialog;

    int top = scene_size.height()/2 - ui->y_centr_top->value(),
        left = scene_size.width()/2 + ui->x_centr_left->value(),
        width = ui->v_r_lenght->value();

    figures.push_back(std::shared_ptr<figure>(new squareC(top, left, width, color, ui->angle_spinBox->value())));
    figures.back()->draw(scene);
}

void MainWindow::draw_rhomb()
{
    QColorDialog* dialog = new QColorDialog();
    dialog->exec();
    QColor color = dialog->currentColor();
    delete dialog;

    int top = scene_size.height()/2 - ui->y_centr_top->value(),
        left = scene_size.width()/2 + ui->x_centr_left->value(),
        h = ui->h_r_height->value(),
        w = ui->v_r_lenght->value();

    figures.push_back(std::shared_ptr<figure>(new rhombus(top, left, w, h, color, ui->angle_spinBox->value())));
    figures.back()->draw(scene);
}
