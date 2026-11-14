
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1640.03 | 0.0190918 | 7211.37ms | 108313 | 4890 | 707064 | 62983.8 | 0.032037 | 3.12085 | 14.1407 | 2.84712 | 0.00383928 | 8.19597e-06 | 3.84216e-06 | 1(Win) | true |
| simdjson (ondemand) | 1549.97 | 0.0799187 | 7579.63ms | 108313 | 320 | 907745 | 66643.6 | 0.141568 | 3.29023 | 15.9077 | 2.34016 | 0.00563823 | 1.09059e-05 | 5.33754e-06 | 2(Loss) | true |
