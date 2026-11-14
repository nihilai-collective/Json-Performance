
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1232.95 | 0.962785 | 9511.5ms | 466906 | 640 | 7.73763e+09 | 361148 | 0.0372804 | 2.46443 | 1(Win) | true |
| Glaze | 1051.4 | 1.04815 | 5467.11ms | 466906 | 640 | 1.26109e+10 | 423508 | 0.663302 | 2.89004 | 2(Loss) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 993.937 | 0.999145 | 5615.12ms | 466906 | 640 | 1.28227e+10 | 447992 | 6.14859 | 3.05684 | -(Loss) | false |
| simdjson (ondemand) DID NOT CONVERGE | 900.657 | 1.07821 | 6348.94ms | 466906 | 160 | 4.54639e+09 | 494391 | 4.07621 | 3.37388 | -(Loss) | false |
