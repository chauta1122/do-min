# do-min
Mục tiêu của dự án nhỏ • 

Lập trình trò chơi quét mìn bằng ngôn ngữ C, không có thư viện bên ngoài, với giao diện văn bản (chế độ bảng điều khiển) (mode console)
• Quản lý các bảng có một hoặc hai kích thước và cấu trúc
 • Sử dụng biểu diễn nhị phân của dữ liệu để mã ngữ nghĩa của vấn đề 
• Sử dụng đệ quy một cách khôn ngoan
 • Chọn các thuật toán hiệu quả và đơn giản để viết mã trò chơi trong C
Yeu cau  của dự án mini:
• Lưới được biểu diễn bằng một mảng byte có kích thước cố định NxN (ví dụ N = 10) và
số lượng mìn là một hằng số (NxN / 5)
• Các ô được mã hóa bằng ngữ nghĩa nhị phân được thấy trong quá trình
• Chương trình bao gồm một hàm void Init_Grid (void)(hàm khởi tạo bảng)
o Đặt bom K trên lưới một cách hiệu quả
o Tính toán số lượng mìn của các ô lân cận một cách hiệu quả và cập nhật
giá trị của các ô tương ứng
Chương trình bao gồm một hàm void Display_Grid (void)(hàm hiển thị bảng)
 o Hiển thị lưới dễ đọc nhất có thể trên bảng điều khiển o Các ô sẽ được hiển thị bởi một ký tự mà bạn chọn tùy thuộc vào ô có được đánh dấu hay không, được đánh dấu hay không và, khi nó được mở mặt nạ, số lượng mìn trong vùng lân cận của nó. 
• Chương trình bao gồm một hàm void Demasque_case (int i, int j): 
o kết thúc nếu chọn trúng bom
nếu ko chọn trúng bom thì mở các ô lân cận theo thuật toán loang.

• trong hàm main gồm các hàm:
o Khởi tạo lưới 
o Để tương tác với người dùng như đã thấy trong courso 
Để quyết định kết thúc trò chơi
