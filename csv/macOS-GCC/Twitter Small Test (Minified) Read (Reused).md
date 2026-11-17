
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2348.22 | 0.705862 | 141.566ms | 2889 | 2560 | 175589 | 1173.3 | 0.348225 | 1(Win) | true |
| Glaze | 1904.32 | 1.60891 | 198.872ms | 2889 | 640 | 346787 | 1446.8 | 1.12083 | 2(Loss) | true |
| Jsonifier (two-stage) | 1705.67 | 1.00786 | 183.288ms | 2889 | 2560 | 678495 | 1615.3 | 1.05731 | 3(Loss) | true |
| simdjson (reflection) | 1299.12 | 0.975826 | 235.455ms | 2889 | 320 | 137055 | 2120.8 | 3.80987 | 4(Loss) | true |
| simdjson (ondemand) | 1010.91 | 0.542732 | 309.274ms | 2889 | 4890 | 1.06992e+06 | 2725.43 | 2.74999 | 5(Loss) | true |
