
----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 849.216 | 0.13508 | 1042.68ms | 2821 | 30 | 549.379 | 3168 | 0.0630915 | 6.1478 | 25.5005 | 4.67246 | 0.00154791 | 0.000129978 | 8.2713e-05 | 1(Win) | true |
| simdjson (ondemand) | 357.424 | 0.0312115 | 1480.44ms | 2821 | 4890 | 26988.5 | 7526.97 | 0.253795 | 14.4706 | 66.5495 | 11.4364 | 0.0117423 | 0.000112797 | 4.66121e-05 | 2(Loss) | true |
