
----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1844.07 | 0.269302 | 9573.18ms | 5212421 | 160 | 8.43187e+09 | 2.69564e+06 | 0.364851 | 2.77335 | 12.5889 | 2.16753 | 0.0100202 | 0.1103 | 0.000923146 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 1833.7 | 0.184797 | 9724.62ms | 5212421 | 40 | 1.00386e+09 | 2.71089e+06 | 0.667238 | 2.73115 | 12.309 | 2.35719 | 0.00985032 | 0.089844 | 0.000177772 | 1(Tie) | true |
