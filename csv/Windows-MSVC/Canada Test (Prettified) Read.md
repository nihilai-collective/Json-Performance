
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1269.14 | 0.747466 | 6275.96ms | 5373214 | 40 | 3.64326e+10 | 4.0376e+06 | 0.189124 | 1.95072 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1253.16 | 0.789736 | 6505.12ms | 5373214 | 80 | 8.34273e+10 | 4.0891e+06 | 1.96808 | 1.97558 | 1(Tie) | true |
| simdjson (ondemand) DID NOT CONVERGE | 439.829 | 0.519508 | 8119.92ms | 5373214 | 40 | 1.46536e+11 | 1.16507e+07 | 6.48782 | 5.62902 | -(Loss) | false |
| Glaze | 419.233 | 0.620966 | 8673.37ms | 5373214 | 40 | 2.30437e+11 | 1.2223e+07 | 0.360521 | 5.90557 | 4(Loss) | true |
