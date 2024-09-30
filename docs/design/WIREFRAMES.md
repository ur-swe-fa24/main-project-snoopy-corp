### Wireframe Dashboards
### 1. **[Login/Sign-Up Screen](/docs/design/png_files/WireframeDashboards/db1)**
   - **Purpose**: This is the entry point for users, allowing them to log in or sign up for access.
   - **User Flow**: After successfully entering credentials, users are directed to different interfaces based on their role (Senior Management or Managers & Engineers).
   - **Design Elements**: It has a clean and simple design with the company branding (Cobotiq), a login form, and a clear distinction of user paths after authentication.

### 2. **[Dashboard for Senior Management](/docs/design/png_files/WireframeDashboards/db2)**
   - **Purpose**: This dashboard is designed for senior management to get a quick overview of operational efficiency and error rates of different robots in use.
   - **Key Metrics**:
     - **Efficiency Rate**: A bar chart visualizing the performance of different types of robots (Scrubber50, Vacuum40, Shampoo) by efficiency percentage.
     - **Error Rate**: A bar chart showing the error rates for the same robot types.
     - **All Robots Overview**: A pie chart giving a quick breakdown of the robot distribution.
   - **Hyperlink**: There is a hyperlink in the upper right corner that leads to a detailed table view dataset, allowing senior management to review the underlying data if needed.
   - **User Experience**: This dashboard is intended to be straightforward and easy to interpret for higher-level decision-makers, with minimal interaction required. The hyperlink offers quick access to a deeper dataset when more granular information is needed.

### 3. **[Dashboard for Building Managers & Field Engineers](/docs/design/png_files/WireframeDashboards/db3)**
   - **Purpose**: This dashboard provides more granular control and deeper analytical capabilities for building managers and field engineers.
   - **Key Features**:
     - **Timelines & Tasks**: Slicers allow users to filter tasks based on start time, end time, and task IDs, giving them the ability to track task progress over time.
     - **Status & Type Filters**: Additional slicers for filtering tasks by their status (completed, in progress, etc.) and robot type (Scrubber50, Vacuum40, Shampoo).
     - **Task Descriptions**: A section providing detailed task information (e.g., cleaned sensors, replaced filters).
   - **Hyperlink**: Similar to the senior management dashboard, this dashboard also features a hyperlink in the upper right corner that leads to a table view of the dataset, offering a detailed look at the raw data for further analysis.
   - **User Experience**: This dashboard allows users to dive into specific data points for task management and troubleshooting, providing more detailed insights compared to the Senior Management dashboard. The hyperlink ensures users can easily transition to a table view dataset for additional data-driven decision-making.
