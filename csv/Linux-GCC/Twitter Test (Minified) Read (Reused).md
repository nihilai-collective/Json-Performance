
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2603.14 | 0.106557 | 5293.06ms | 466906 | 640 | 2.12623e+07 | 171053 | 0.156189 | 1.9263 | 6.38775 | 0.989802 | 0.0089482 | 0.00125823 | 6.32655e-05 | 1(Win) | true |
| Glaze | 2213.06 | 0.0998977 | 6015.74ms | 466906 | 640 | 2.58562e+07 | 201204 | 0.0258332 | 2.27191 | 8.98747 | 1.54305 | 0.00814616 | 0.000560953 | 1.25059e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2146.44 | 0.0654064 | 6309.96ms | 466906 | 1280 | 2.35651e+07 | 207448 | 0.368403 | 2.33842 | 7.59415 | 1.10742 | 0.0124993 | 0.00599198 | 7.98558e-05 | 3(Loss) | true |
| simdjson (reflection) | 1853.34 | 0.116556 | 7036.54ms | 466906 | 640 | 5.01877e+07 | 240256 | 0.294402 | 2.71372 | 9.10785 | 1.2843 | 0.00933185 | 0.0185975 | 1.5685e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1325.85 | 0.0747759 | 9460.05ms | 466906 | 1280 | 8.07246e+07 | 335843 | 0.24006 | 3.76804 | 11.8187 | 2.45214 | 0.0106542 | 0.0147757 | 1.82987e-05 | 5(Loss) | true |
