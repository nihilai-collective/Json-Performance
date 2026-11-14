
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1057.66 | 0.559796 | 7837.27ms | 5212421 | 40 | 2.7689e+10 | 4.69996e+06 | 0.154993 | 2.87341 | 1(Win) | true |
| simdjson (ondemand) | 981.592 | 0.492933 | 8357.16ms | 5212421 | 80 | 4.98521e+10 | 5.06417e+06 | 0.0947184 | 3.09595 | 2(Loss) | true |
