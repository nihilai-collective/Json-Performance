
----
### Github Events Test (Minified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17685.1 | 0.032171 | 1005.97ms | 53331 | 4890 | 4185.85 | 2875.89 | 0.182954 | 0.29518 | 1.56633 | 0.0780785 | 5.81697e-05 | 2.56146e-06 | 3.41273e-07 | 1(Win) | true |
| simdjson (stage-1) | 15474 | 0.0268479 | 1046.29ms | 53331 | 4890 | 3807.9 | 3286.84 | 0.141809 | 0.33726 | 1.56335 | 0.0662467 | 3.29347e-05 | 2.80304e-06 | 6.48034e-07 | 2(Loss) | true |
