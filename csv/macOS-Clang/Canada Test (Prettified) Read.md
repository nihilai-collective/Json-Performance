
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1529.32 | 0.0637488 | 5140.92ms | 5373214 | 80 | 3.6501e+08 | 3.3507e+06 | 0.104735 | 1(Win) | true |
| Jsonifier (two-stage) | 1415.13 | 0.0414305 | 5552.29ms | 5373214 | 40 | 9.00275e+07 | 3.62107e+06 | 0.0310884 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 1205.06 | 0.935094 | 6490.36ms | 5373214 | 30 | 4.74332e+10 | 4.25231e+06 | 1.47859 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1195.01 | 0.0710854 | 6539.01ms | 5373214 | 30 | 2.78747e+08 | 4.28809e+06 | 0.0265836 | 3(Tie) | true |
