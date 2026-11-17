
----
### Instruments Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 660.129 | 0.0639516 | 8550.41ms | 108313 | 80 | 801119 | 156477 | 0.219747 | 7.80112 | 37.3763 | 7.43234 | 0.010679 | 1.45412e-05 | 5.77031e-06 | 1(Win) | true |
| simdjson (ondemand) | 248.189 | 0.0675656 | 5432.53ms | 108313 | 640 | 5.06088e+07 | 416196 | 0.0235366 | 20.6262 | 99.4376 | 17.9773 | 0.0703087 | 3.90939e-05 | 1.82919e-05 | 2(Loss) | true |
