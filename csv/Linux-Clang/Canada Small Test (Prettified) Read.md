
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2266.7 | 0.457048 | 490.944ms | 11579 | 320 | 158646 | 4871.67 | 0.272271 | 1.08645 | 1(Win) | true |
| Jsonifier | 2070.86 | 0.139805 | 543.512ms | 11579 | 30 | 1667.27 | 5332.37 | 0.0249983 | 1.18977 | 2(Loss) | true |
| simdjson (ondemand) | 1716.43 | 0.225387 | 651.779ms | 11579 | 40 | 8410.2 | 6433.45 | 0.152301 | 1.43596 | 3(Loss) | true |
| Glaze | 1581.39 | 0.192652 | 698.983ms | 11579 | 1280 | 231645 | 6982.86 | 0.0146431 | 1.55989 | 4(Loss) | true |
