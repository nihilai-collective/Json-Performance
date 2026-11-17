
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1821.83 | 0.0880742 | 6688.56ms | 124597 | 1280 | 4.22382e+06 | 65222.7 | 0.28194 | 1.35843 | 1(Win) | true |
| Jsonifier (two-stage) | 1708 | 0.0759789 | 7038.31ms | 124597 | 2560 | 7.15261e+06 | 69569.6 | 0.0972937 | 1.449 | 2(Loss) | true |
| Jsonifier STATISTICAL TIE | 1690.13 | 0.482485 | 7088.79ms | 124597 | 40 | 4.60259e+06 | 70305.1 | 0.083658 | 1.46433 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1677.77 | 0.10043 | 7167.56ms | 124597 | 1280 | 6.47577e+06 | 70823.1 | 0.404317 | 1.47512 | 3(Tie) | true |
| Glaze | 1655.89 | 0.17693 | 7289.01ms | 124597 | 160 | 2.57916e+06 | 71759.2 | 0.00249103 | 1.49462 | 5(Loss) | true |
