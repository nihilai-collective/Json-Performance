
----
### Random Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 627.556 | 0.0831095 | 839.981ms | 4926 | 2560 | 99088.7 | 7485.86 | 0.00730597 | 4.83088 | 1(Win) | true |
| simdjson (ondemand) | 386.247 | 0.19542 | 1346.08ms | 4926 | 2560 | 1.44623e+06 | 12162.7 | 0.350978 | 7.85635 | 2(Loss) | true |
