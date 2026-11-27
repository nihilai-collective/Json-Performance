
----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1494.01 | 0.0906749 | 914.34ms | 11579 | 80 | 3593.35 | 7391.25 | 0.118524 | 1.65028 | 1(Win) | true |
| Jsonifier | 1394.89 | 0.374583 | 956.305ms | 11579 | 1280 | 1.12557e+06 | 7916.48 | 0.341632 | 1.76879 | 2(Loss) | true |
| simdjson (ondemand) | 449.981 | 0.250148 | 2658.81ms | 11579 | 640 | 2.41173e+06 | 24540.2 | 0.0260984 | 5.49616 | 3(Loss) | true |
| Glaze | 413.735 | 0.0605208 | 2923.6ms | 11579 | 30 | 7827.59 | 26690 | 0.300639 | 5.977 | 4(Loss) | true |
