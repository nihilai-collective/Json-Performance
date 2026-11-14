
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 243.468 | 0.368182 | 514.725ms | 1811 | 160 | 109143 | 7093.75 | 1.50989 | 10.1302 | 1(Win) | true |
| simdjson (ondemand) | 138.666 | 0.316063 | 1269.32ms | 1811 | 640 | 991804 | 12455.2 | 0.00878073 | 17.8151 | 2(Loss) | true |
