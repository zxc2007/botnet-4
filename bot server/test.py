class Car:

     # thuộc tính lớp
     loaixe = "Ô tô"

     # thuộc tính đối tượng
     def __init__(self, tenxe, mausac, nguyenlieu):
        self.tenxe = tenxe
        self.mausac = mausac
        self.nguyenlieu = nguyenlieu

# instantiate the Car class
toyota = Car("Toyota", "Đỏ", "Điện")
lamborghini = Car("Lamborghini", "Vàng", "Deisel")
porsche = Car("Porsche", "Xanh", "Gas")

# access the class attributes
print("Porsche là {}.".format(porsche.loaixe))
print("Toyota là {}.".format(toyota.__class__.loaixe))
print("Lamborghini cũng là {}.".format(lamborghini.__class__.loaixe))

# access the instance attributes
print("Xe {} có màu {}. {} là nguyên liệu vận hành.".format( toyota.tenxe, toyota.mausac, toyota.nguyenlieu))
print("Xe {} có màu {}. {} là nguyên liệu vận hành.".format( lamborghini.tenxe, lamborghini.mausac,lamborghini.nguyenlieu))
print("Xe {} có màu {}. {} là nguyên liệu vận hành.".format( porsche.tenxe, porsche.mausac, porsche.nguyenlieu))