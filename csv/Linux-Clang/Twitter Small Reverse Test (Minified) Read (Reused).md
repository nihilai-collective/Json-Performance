
----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 915.203 | 0.110459 | 1022.6ms | 2821 | 640 | 6747.64 | 2939.58 | 0.025999 | 5.63096 | 24.0259 | 4.44027 | 0.00140797 | 4.54183e-05 | 7.75434e-06 | 1(Win) | true |
| simdjson (ondemand) | 354.766 | 0.050666 | 1490.4ms | 2821 | 2560 | 37791.7 | 7583.35 | 0.248321 | 14.542 | 66.5285 | 11.4169 | 0.013655 | 0.000106345 | 6.12039e-05 | 2(Loss) | true |
