
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1973.95 | 0.101452 | 2777.55ms | 56369 | 2560 | 1.95419e+06 | 27233.5 | 0.240712 | 1.25295 | 1(Win) | true |
| Jsonifier (two-stage) | 1751.52 | 0.170028 | 3116.14ms | 56369 | 320 | 871444 | 30692 | 0.16374 | 1.41223 | 2(Loss) | true |
| simdjson (reflection) | 1652.03 | 0.0890171 | 3270.59ms | 56369 | 2560 | 2.14797e+06 | 32540.3 | 0.213129 | 1.49742 | 3(Loss) | true |
| Glaze | 1590.63 | 0.274997 | 3296.82ms | 56369 | 80 | 691019 | 33796.5 | 0.274114 | 1.55523 | 4(Loss) | true |
| simdjson (ondemand) | 1436.81 | 0.218169 | 3870.37ms | 56369 | 160 | 1.06609e+06 | 37414.7 | 0.0423475 | 1.72193 | 5(Loss) | true |
