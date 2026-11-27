
----
### Validate Test Read Results [(Here is the data we used for this test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2598.54 | 0.127683 | 6117.2ms | 631514 | 160 | 1.40118e+07 | 231768 | 1.03522 | 1(Win) | true |
| Glaze | 1991.1 | 0.084078 | 8007.36ms | 631514 | 640 | 4.13929e+07 | 302476 | 0.0192222 | 2(Loss) | true |
