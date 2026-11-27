
----
### Google Maps Response Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1584.38 | 0.137068 | 1481.39ms | 11812 | 40 | 3798.91 | 7109.9 | 0.0281377 | 3.21058 | 15.7365 | 2.95733 | 0.00421817 | 1.69319e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1182.83 | 0.0847522 | 1745.33ms | 11812 | 30 | 1954.46 | 9523.6 | 0.0584171 | 4.37439 | 18.2208 | 3.37072 | 0.00828818 | 2.82199e-05 | 1.69319e-05 | 2(Loss) | true |
