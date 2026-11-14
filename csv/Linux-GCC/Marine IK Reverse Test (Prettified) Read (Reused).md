
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1453.74 | 0.241117 | 7472.42ms | 7351818 | 30 | 4.05689e+09 | 4.8229e+06 | 0.0560503 | 1.70306 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 903.119 | 0.204961 | 5676.39ms | 7351818 | 40 | 1.01275e+10 | 7.76337e+06 | 2.66983 | 2.7414 | -(Loss) | false |
