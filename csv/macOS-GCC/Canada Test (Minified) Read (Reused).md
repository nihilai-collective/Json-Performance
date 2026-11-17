
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 759.585 | 0.950908 | 5219.03ms | 2251027 | 80 | 5.77799e+10 | 2.82621e+06 | 0.436115 | 1(Win) | true |
| simdjson (reflection) | 681.634 | 0.774127 | 5967.64ms | 2251027 | 30 | 1.78322e+10 | 3.14941e+06 | 3.36279 | 2(Loss) | true |
| Glaze | 631.996 | 1.43557 | 6229.62ms | 2251027 | 30 | 7.1335e+10 | 3.39677e+06 | 1.35072 | 3(Loss) | true |
| simdjson (ondemand) | 551.576 | 0.759033 | 6675.45ms | 2251027 | 80 | 6.98172e+10 | 3.89203e+06 | 3.86153 | 4(Loss) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 505.295 | 1.10739 | 6471.4ms | 2251027 | 40 | 8.85386e+10 | 4.24851e+06 | 12.7779 | -(Loss) | false |
