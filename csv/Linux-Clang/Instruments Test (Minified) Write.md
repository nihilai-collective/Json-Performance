
----
### Instruments Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16501.4 | 0.112344 | 1372.17ms | 108313 | 1280 | 63303.9 | 6259.79 | 0.0122573 | 0.308153 | 1.46189 | 0.198342 | 0.000174891 | 4.10414e-06 | 1.39209e-06 | 1(Win) | true |
| Glaze | 4788.32 | 0.0771984 | 2903.79ms | 108313 | 4890 | 1.35619e+06 | 21572.4 | 0.0729119 | 1.06019 | 3.26116 | 0.410874 | 0.000279735 | 1.53932e-05 | 7.0556e-06 | 2(Loss) | true |
