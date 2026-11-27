
----
### Twitter Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 701.54 | 0.212609 | 392.115ms | 2821 | 4890 | 325067 | 3834.87 | 0.74105 | 1(Win) | true |
| simdjson (ondemand) | 301.931 | 0.139678 | 913.074ms | 2821 | 4890 | 757454 | 8910.37 | 0.037352 | 2(Loss) | true |
