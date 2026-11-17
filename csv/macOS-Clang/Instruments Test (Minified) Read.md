
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2414.84 | 0.246302 | 4294.12ms | 108313 | 2560 | 2.84157e+07 | 42775.2 | 0.738884 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1418.16 | 0.783614 | 6853.68ms | 108313 | 640 | 2.08495e+08 | 72837.6 | 0.713147 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1406.59 | 0.335511 | 7617.71ms | 108313 | 80 | 4.85661e+06 | 73436.9 | 0.228584 | 2(Tie) | true |
| simdjson (ondemand) | 618.574 | 0.866661 | 8167.66ms | 108313 | 160 | 3.35117e+08 | 166989 | 0.275076 | 4(Loss) | true |
