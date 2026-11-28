
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 911.236 | 0.544055 | 185.278ms | 1811 | 4890 | 519960 | 1895.34 | 3.64425 | 1(Win) | true |
| Glaze | 833.866 | 1.68524 | 185.98ms | 1811 | 640 | 779739 | 2071.2 | 0.7393 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 247.663 | 0.556186 | 724.99ms | 1811 | 1280 | 1.92559e+06 | 6973.6 | 0.0746226 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 244.162 | 1.40153 | 655.307ms | 1811 | 160 | 1.57255e+06 | 7073.6 | 1.05192 | 3(Tie) | true |
