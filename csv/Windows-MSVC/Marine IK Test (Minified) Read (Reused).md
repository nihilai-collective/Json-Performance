
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 244.974 | 0.574012 | 5334.86ms | 1834197 | 30 | 5.03984e+10 | 7.14047e+06 | 2.15782 | 10.1065 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 219.074 | 1.14061 | 5675.55ms | 1834197 | 30 | 2.48834e+11 | 7.98464e+06 | 4.12063 | 11.3011 | -(Loss) | false |
