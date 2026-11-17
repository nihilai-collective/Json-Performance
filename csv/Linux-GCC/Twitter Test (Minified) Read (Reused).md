
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2606.54 | 0.0762394 | 5313.72ms | 466906 | 1280 | 2.1712e+07 | 170830 | 0.121447 | 1.92009 | 6.38826 | 0.99016 | 0.00876273 | 0.00249662 | 3.88127e-05 | 1(Win) | true |
| Glaze | 2272.38 | 0.151747 | 5889.58ms | 466906 | 320 | 2.82936e+07 | 195952 | 0.0826258 | 2.20874 | 8.98589 | 1.54247 | 0.00684852 | 0.00141519 | 2.33117e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2170.83 | 0.067801 | 6237.22ms | 466906 | 1280 | 2.47565e+07 | 205118 | 0.100476 | 2.30343 | 7.59207 | 1.107 | 0.0128774 | 0.00819924 | 2.09139e-05 | 3(Loss) | true |
| simdjson (reflection) | 1868 | 0.379567 | 7024.48ms | 466906 | 80 | 6.54895e+07 | 238370 | 0.0408775 | 2.68373 | 9.10561 | 1.2836 | 0.00871731 | 0.0176536 | 4.92337e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1335.14 | 0.107166 | 9396.26ms | 466906 | 640 | 8.17514e+07 | 333504 | 0.253354 | 3.73862 | 11.8194 | 2.45234 | 0.0105463 | 0.0110172 | 3.86554e-05 | 5(Loss) | true |
