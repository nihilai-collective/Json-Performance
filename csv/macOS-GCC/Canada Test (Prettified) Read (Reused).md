
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1782.53 | 0.877277 | 5319.29ms | 5373214 | 30 | 1.90805e+10 | 2.87473e+06 | 0.475932 | 1(Win) | true |
| Jsonifier (two-stage) | 1606.46 | 1.14778 | 5624.13ms | 5373214 | 80 | 1.07235e+11 | 3.1898e+06 | 2.41465 | 2(Loss) | true |
| simdjson (reflection) | 1442.22 | 0.523587 | 6385.33ms | 5373214 | 80 | 2.76867e+10 | 3.55306e+06 | 0.526202 | 3(Loss) | true |
| Glaze | 1311.76 | 0.743627 | 7099.27ms | 5373214 | 40 | 3.37546e+10 | 3.90644e+06 | 1.79896 | 4(Loss) | true |
| simdjson (ondemand) | 1271.26 | 0.661959 | 6984.83ms | 5373214 | 80 | 5.69576e+10 | 4.03088e+06 | 0.63779 | 5(Loss) | true |
