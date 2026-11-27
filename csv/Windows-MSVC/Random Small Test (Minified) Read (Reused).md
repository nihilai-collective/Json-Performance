
----
### Random Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 921.773 | 0.0981622 | 613.582ms | 4926 | 1280 | 32036.1 | 5096.48 | 0.0506119 | 3.28494 | 1(Win) | true |
| simdjson (ondemand) | 763.908 | 0.18169 | 714.58ms | 4926 | 4890 | 610486 | 6149.69 | 0.0878274 | 3.96618 | 2(Loss) | true |
