
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1621.79 | 0.0294508 | 4418.16ms | 53331 | 2560 | 218376 | 31360.7 | 0.175335 | 3.1775 | 11.7509 | 2.24174 | 0.0104883 | 1.9117e-05 | 8.69423e-06 | 1(Win) | true |
| simdjson (ondemand) | 1186.35 | 0.0357983 | 5582.2ms | 53331 | 2560 | 602973 | 42871.3 | 0.0422854 | 4.341 | 16.6658 | 2.99762 | 0.017118 | 1.52643e-05 | 3.47183e-06 | 2(Loss) | true |
