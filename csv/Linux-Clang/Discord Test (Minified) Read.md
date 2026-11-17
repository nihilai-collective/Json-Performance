
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2221.28 | 0.0984658 | 3177.5ms | 56369 | 1280 | 726867 | 24201.2 | 0.0397672 | 2.28111 | 9.3505 | 1.89418 | 0.00518682 | 7.21668e-05 | 4.63464e-05 | 1(Win) | true |
| Glaze | 1864.94 | 0.155632 | 3650.78ms | 56369 | 640 | 1.28803e+06 | 28825.4 | 0.0446347 | 2.71309 | 11.633 | 2.33826 | 0.00587025 | 0.000103476 | 6.198e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1723.49 | 0.182512 | 3849.3ms | 56369 | 320 | 1.03704e+06 | 31191.1 | 0.012522 | 2.92555 | 12.2764 | 2.27964 | 0.00827954 | 8.44325e-05 | 5.38306e-05 | 3(Loss) | true |
| simdjson (ondemand) | 964.684 | 0.0693255 | 6358.88ms | 56369 | 2560 | 3.82064e+06 | 55725.7 | 0.0548061 | 5.20229 | 21.9236 | 3.62652 | 0.0115303 | 0.000101438 | 6.27423e-05 | 4(Loss) | true |
