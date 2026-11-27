
----
### Validate Test Read Results [(Here is the data we used for this test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2948.2 | 0.739305 | 5422.02ms | 631514 | 30 | 6.84258e+07 | 204280 | 0.0603382 | 0.83961 | 1(Win) | true |
| Glaze | 2432.79 | 0.182839 | 6497.88ms | 631514 | 1280 | 2.62243e+08 | 247559 | 0.767988 | 1.01756 | 2(Loss) | true |
