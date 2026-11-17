
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 985.084 | 0.381577 | 9261.31ms | 94653 | 2560 | 3.12988e+08 | 91635 | 1.69576 | 1(Win) | true |
| Glaze | 927.782 | 0.173873 | 9250.23ms | 94653 | 4890 | 1.39942e+08 | 97294.5 | 0.271117 | 2(Loss) | true |
| Jsonifier (two-stage) | 790.29 | 0.275634 | 5891.78ms | 94653 | 2560 | 2.53747e+08 | 114222 | 0.296175 | 3(Loss) | true |
| simdjson (reflection) | 772.031 | 0.256268 | 6055.31ms | 94653 | 2560 | 2.29842e+08 | 116923 | 0.557732 | 4(Loss) | true |
| simdjson (ondemand) | 628.022 | 0.527942 | 7635.09ms | 94653 | 640 | 3.68528e+08 | 143734 | 1.82923 | 5(Loss) | true |
