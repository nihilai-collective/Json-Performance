
----
### Google Maps Response Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1030.24 | 0.0594879 | 2459.27ms | 25388 | 4890 | 955756 | 23501.2 | 0.386378 | 2.94707 | 1(Win) | true |
| simdjson (ondemand) | 982.089 | 0.0436255 | 2562.17ms | 25388 | 4890 | 565647 | 24653.5 | 0.0650805 | 3.09192 | 2(Loss) | true |
