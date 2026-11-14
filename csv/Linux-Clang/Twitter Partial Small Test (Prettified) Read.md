
----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6824.22 | 0.35611 | 785.531ms | 3808 | 160 | 574.615 | 532.163 | 0.0822794 | 0.814008 | 3.18592 | 0.3448 | 0.000426733 | 2.29779e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6689.21 | 0.298772 | 781.441ms | 3808 | 4890 | 12865.7 | 542.903 | 0.18853 | 0.826106 | 3.28624 | 0.405987 | 0.000269049 | 3.46381e-05 | 1.29423e-05 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 6635.58 | 0.348913 | 781.919ms | 3808 | 320 | 1166.87 | 547.291 | 0.127494 | 0.819626 | 3.28625 | 0.405992 | 0.000276556 | 3.77495e-05 | 3.28256e-06 | 2(Tie) | true |
| Glaze | 3351.39 | 0.124461 | 839.555ms | 3808 | 4890 | 8894.47 | 1083.61 | 0.362657 | 1.57557 | 6.48057 | 1.20746 | 0.000524834 | 3.70547e-05 | 1.09016e-05 | 4(Loss) | true |
