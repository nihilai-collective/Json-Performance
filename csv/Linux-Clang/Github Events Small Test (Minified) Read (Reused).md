
----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2998.39 | 0.0594376 | 67.0797ms | 1691 | 320 | 32.7028 | 537.844 | 0.453457 | 0.784946 | 1(Win) | true |
| Jsonifier (two-stage) | 2524.84 | 0.144712 | 71.7109ms | 1691 | 160 | 136.694 | 638.719 | 0.833744 | 0.938054 | 2(Loss) | true |
| Glaze | 2259.34 | 0.072496 | 80.9801ms | 1691 | 160 | 42.8421 | 713.775 | 0.104965 | 1.05461 | 3(Loss) | true |
| simdjson (ondemand) | 1601.08 | 0.273688 | 110.991ms | 1691 | 30 | 227.978 | 1007.23 | 0.405383 | 1.50164 | 4(Loss) | true |
