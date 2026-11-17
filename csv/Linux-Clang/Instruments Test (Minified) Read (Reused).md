
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2855.99 | 0.0301456 | 4550.51ms | 108313 | 4890 | 581309 | 36168 | 0.00659327 | 1.77075 | 7.95652 | 1.57473 | 0.00252325 | 1.13943e-05 | 6.60058e-06 | 1(Win) | true |
| Glaze | 2572.86 | 0.202243 | 4992.46ms | 108313 | 640 | 4.21946e+06 | 40148.1 | 0.241119 | 1.95901 | 9.81131 | 1.71501 | 0.00248712 | 1.82053e-05 | 9.89609e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2146.8 | 0.0821905 | 5746.92ms | 108313 | 4890 | 7.64768e+06 | 48115.9 | 0.106553 | 2.34931 | 11.0341 | 1.88943 | 0.00267418 | 1.33937e-05 | 7.6711e-06 | 3(Loss) | true |
| simdjson (ondemand) | 790.111 | 0.185619 | 7160ms | 108313 | 320 | 1.88442e+07 | 130735 | 0.0648151 | 6.30837 | 27.7974 | 4.32845 | 0.0036458 | 3.10731e-05 | 1.67339e-05 | 4(Loss) | true |
