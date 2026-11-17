
----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1665.53 | 0.105015 | 1048.08ms | 4926 | 4890 | 42903.8 | 2820.6 | 0.105762 | 3.12139 | 13.962 | 2.59968 | 0.00381511 | 4.10575e-05 | 6.22713e-06 | 1(Win) | true |
| simdjson (ondemand) | 1266.82 | 0.0678943 | 1127.38ms | 4926 | 1280 | 8113.96 | 3708.33 | 0.0174829 | 4.10867 | 15.8975 | 2.86703 | 0.00380078 | 4.18697e-05 | 1.42738e-06 | 2(Loss) | true |
