
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1604.27 | 0.200887 | 3386.56ms | 56369 | 2560 | 1.16003e+07 | 33509.1 | 2.10948 | 1(Win) | true |
| Glaze | 1219.06 | 0.207272 | 4411.96ms | 56369 | 4890 | 4.08525e+07 | 44097.5 | 0.648763 | 2(Loss) | true |
| Jsonifier (two-stage) | 1102.75 | 1.52941 | 5115.92ms | 56369 | 40 | 2.22348e+07 | 48748.8 | 0.370596 | 3(Loss) | true |
| simdjson (reflection) | 1014.82 | 0.619443 | 5556.38ms | 56369 | 80 | 8.61388e+06 | 52972.8 | 0.132722 | 4(Loss) | true |
| simdjson (ondemand) | 881.678 | 0.456564 | 6616.96ms | 56369 | 640 | 4.95958e+07 | 60972 | 1.38209 | 5(Loss) | true |
