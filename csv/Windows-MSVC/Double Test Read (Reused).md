
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1132.99 | 0.223365 | 163.864ms | 1811 | 160 | 1854.95 | 1524.38 | 0.123153 | 2.14133 | 1(Win) | true |
| Glaze | 490.829 | 0.124799 | 349.287ms | 1811 | 80 | 1542.72 | 3518.75 | 0.177936 | 4.99971 | 2(Loss) | true |
| simdjson (ondemand) | 369.83 | 0.182219 | 493.721ms | 1811 | 30 | 2172.41 | 4670 | 0.213675 | 6.65187 | 3(Loss) | true |
