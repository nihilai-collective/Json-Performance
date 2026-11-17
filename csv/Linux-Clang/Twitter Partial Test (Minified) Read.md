
----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8176.22 | 0.0775996 | 6200.97ms | 466906 | 1280 | 2.28603e+06 | 54459.9 | 0.00301675 | 0.615284 | 3.05574 | 0.390944 | 0.00106632 | 8.32943e-06 | 5.17871e-06 | 1(Win) | true |
| Jsonifier | 8146.48 | 0.0622742 | 6225.45ms | 466906 | 2560 | 2.96603e+06 | 54658.7 | 0.00824073 | 0.617997 | 3.06665 | 0.393769 | 0.00109965 | 6.26966e-06 | 3.79995e-06 | 2(Loss) | true |
| simdjson (ondemand) | 6884.05 | 0.0840203 | 7230.28ms | 466906 | 1280 | 3.78051e+06 | 64682.3 | 0.0209771 | 0.730928 | 3.47925 | 0.380335 | 0.000865071 | 1.71324e-05 | 1.1005e-05 | 3(Loss) | true |
| Glaze | 3400.23 | 0.0231485 | 7078.28ms | 466906 | 2560 | 2.35249e+06 | 130955 | 0.039746 | 1.48905 | 5.74337 | 0.996749 | 0.00175512 | 2.4621e-05 | 1.81213e-05 | 4(Loss) | true |
