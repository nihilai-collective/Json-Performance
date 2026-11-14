
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2276.16 | 0.142824 | 5043.17ms | 466906 | 320 | 2.49806e+07 | 195626 | 0.0265568 | 1(Win) | true |
| Glaze | 1775.2 | 0.245918 | 6484.14ms | 466906 | 40 | 1.52196e+07 | 250831 | 0.0412133 | 2(Loss) | true |
| Jsonifier (two-stage) | 1755.94 | 0.132718 | 6472.74ms | 466906 | 320 | 3.62451e+07 | 253583 | 0.16001 | 3(Loss) | true |
| simdjson (ondemand) | 838.825 | 0.083859 | 6766.76ms | 466906 | 640 | 1.26822e+08 | 530834 | 0.0268262 | 4(Loss) | true |
