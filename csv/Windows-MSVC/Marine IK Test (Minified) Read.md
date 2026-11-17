
----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7956.18 | 0.0615826 | 5614.94ms | 1834197 | 320 | 5.86609e+06 | 219858 | 0.207091 | 0.38183 | 1(Win) | true |
| simdjson (stage-1) | 6689.69 | 0.0856828 | 6619.65ms | 1834197 | 640 | 3.21253e+07 | 261481 | 0.213004 | 0.454161 | 2(Loss) | true |
