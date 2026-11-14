
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1080.7 | 0.307607 | 5629.96ms | 124597 | 2560 | 2.92842e+08 | 109951 | 0.021925 | 2.81166 | 1(Win) | true |
| Jsonifier (two-stage) | 1068.49 | 0.340855 | 5688.37ms | 124597 | 2560 | 3.67837e+08 | 111208 | 0.104044 | 2.8438 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 959.003 | 0.325417 | 6333.34ms | 124597 | 2560 | 4.16195e+08 | 123905 | 0.256872 | 3.16847 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 953.466 | 0.222484 | 6368ms | 124597 | 2560 | 1.96808e+08 | 124624 | 0.294245 | 3.18698 | 3(Tie) | true |
