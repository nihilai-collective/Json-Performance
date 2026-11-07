
----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 772.15 | 0.190103 | 729.215ms | 4630 | 4890 | 577894 | 5718.47 | 0.292353 | 3.1922 | 1(Win) | true |
| Jsonifier (two-stage) | 724.151 | 0.171077 | 787.767ms | 4630 | 40 | 4352.56 | 6097.5 | 0.0136687 | 3.39908 | 2(Loss) | true |
| Glaze | 187.03 | 0.0920126 | 2534.11ms | 4630 | 4890 | 2.30751e+06 | 23608.6 | 0.083751 | 13.2223 | 3(Loss) | true |
| simdjson (ondemand) | 186.459 | 0.11903 | 2544.88ms | 4630 | 2560 | 2.03398e+06 | 23680.8 | 0.0179832 | 13.2637 | 4(Loss) | true |
