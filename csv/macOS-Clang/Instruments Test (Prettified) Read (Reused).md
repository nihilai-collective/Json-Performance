
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3128.44 | 0.0732233 | 5896.67ms | 183677 | 4890 | 8.21982e+06 | 55992.2 | 0.101303 | 1(Win) | true |
| Jsonifier (two-stage) | 2778.01 | 0.136229 | 6657.54ms | 183677 | 320 | 2.36118e+06 | 63055.3 | 0.0142108 | 2(Loss) | true |
| Glaze | 2048.06 | 0.113808 | 8836.89ms | 183677 | 1280 | 1.21276e+07 | 85528.6 | 0.0213662 | 3(Loss) | true |
| simdjson (ondemand) | 1165.03 | 0.138756 | 7853.89ms | 183677 | 320 | 1.39281e+07 | 150355 | 0.110521 | 4(Loss) | true |
