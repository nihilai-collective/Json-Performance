
----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1287.45 | 0.35144 | 375.198ms | 4857 | 2560 | 409280 | 3597.81 | 0.488784 | 2.34781 | 1(Win) | true |
| Jsonifier (two-stage) | 1008.42 | 0.389632 | 482.666ms | 4857 | 30 | 9609.2 | 4593.33 | 0.361533 | 3.00165 | 2(Loss) | true |
| Glaze | 998.275 | 0.284868 | 504.006ms | 4857 | 30 | 5241.38 | 4640 | 0.429185 | 3.03378 | 3(Loss) | true |
| simdjson (ondemand) | 740.083 | 0.533029 | 654.364ms | 4857 | 80 | 89036.4 | 6258.75 | 0.380914 | 4.09434 | 4(Loss) | true |
