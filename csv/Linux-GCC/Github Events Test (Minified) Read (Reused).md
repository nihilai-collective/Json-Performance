
----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1656.58 | 0.0600943 | 4336.85ms | 53331 | 640 | 217861 | 30702 | 0.420237 | 3.06269 | 11.1982 | 2.1112 | 0.00957417 | 6.41337e-05 | 4.75509e-05 | 1(Win) | true |
| simdjson (ondemand) | 1230.45 | 0.0787961 | 5423.72ms | 53331 | 4890 | 5.18738e+06 | 41334.7 | 0.1196 | 4.14782 | 15.5931 | 3.00155 | 0.0166892 | 7.16903e-05 | 4.69576e-05 | 2(Loss) | true |
