
----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 23324.3 | 0.185022 | 7729.75ms | 1834197 | 640 | 1.23226e+07 | 74995.9 | 0.140227 | 0.106108 | 1(Win) | true |
| simdjson (stage-1) | 18604.8 | 0.140138 | 9602.5ms | 1834197 | 640 | 1.11105e+07 | 94020 | 0.316085 | 0.133032 | 2(Loss) | true |
