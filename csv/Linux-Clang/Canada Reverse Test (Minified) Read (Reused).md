
----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 848.783 | 0.107143 | 8497.86ms | 2090234 | 30 | 1.89952e+08 | 2.34854e+06 | 0.0771911 | 5.98715 | 30.3634 | 5.70543 | 0.0219187 | 0.131556 | 8.26542e-05 | 1(Win) | true |
| simdjson (ondemand) | 806.754 | 0.12315 | 8850.35ms | 2090234 | 30 | 2.77777e+08 | 2.47089e+06 | 0.0411775 | 6.27755 | 30.7467 | 5.3204 | 0.0218448 | 0.155711 | 0.000158882 | 2(Loss) | true |
