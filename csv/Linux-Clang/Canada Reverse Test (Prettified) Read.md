
----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1491.44 | 0.262708 | 10265.7ms | 5212421 | 160 | 1.22669e+10 | 3.33299e+06 | 0.457746 | 1.66002 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1336.72 | 0.298016 | 5516.03ms | 5212421 | 80 | 9.82578e+09 | 3.71876e+06 | 3.43288 | 1.85215 | -(Loss) | false |
