
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 991.221 | 2.29919 | 193.347ms | 1811 | 160 | 256783 | 1742.4 | 3.28597 | 1(Win) | true |
| Glaze | 921.614 | 1.00905 | 198.266ms | 1811 | 640 | 228846 | 1874 | 0.530786 | 2(Loss) | true |
| simdjson (ondemand) | 277.402 | 0.38961 | 624.286ms | 1811 | 1280 | 753160 | 6226 | 0.384 | 3(Loss) | true |
| simdjson (reflection) | 272.453 | 0.226042 | 657.032ms | 1811 | 2560 | 525623 | 6339.1 | 0.631721 | 4(Loss) | true |
